#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    // Sistema de combustíveis
    const int NUM_COMBUSTIVEIS = 4;
    string nomes_combustiveis[] = {"Gasolina", "Etanol", "Diesel", "Gas"};
    string unidades_combustiveis[] = {"L", "L", "L", "m3"};
    double precos_combustiveis[] = {5.80, 4.20, 6.50, 4.90};
    double consumos_combustiveis[] = {10.0, 8.5, 25.0, 13.5};
    
    // Sistema de cidades
    const int NUM_CIDADES = 15;
    string cidades[] = {
        "Sao Paulo/SP", "Rio de Janeiro/RJ", "Belo Horizonte/MG",
        "Brasilia/DF", "Salvador/BA", "Fortaleza/CE", "Recife/PE",
        "Curitiba/PR", "Porto Alegre/RS", "Goiania/GO",
        "Manaus/AM", "Belem/PA", "Florianopolis/SC", "Vitoria/ES",
        "Campinas/SP"
    };
    
    // Matriz de distâncias
    double distancias[15][15] = {
        {0, 430, 586, 1015, 1962, 2850, 2390, 408, 1109, 925, 3500, 2600, 705, 881, 99},
        {430, 0, 434, 1148, 1649, 2350, 2180, 852, 1553, 1340, 3200, 2400, 1135, 521, 360},
        {586, 434, 0, 716, 1372, 2250, 1970, 1004, 1710, 906, 3100, 2200, 1410, 524, 583},
        {1015, 1148, 716, 0, 1443, 2200, 2209, 1367, 2027, 209, 2700, 1800, 1730, 1190, 873},
        {1962, 1649, 1372, 1443, 0, 1389, 839, 2330, 3010, 1640, 4200, 1600, 2980, 1200, 1860},
        {2850, 2350, 2250, 2200, 1389, 0, 800, 3460, 3910, 2390, 3300, 1600, 3720, 1850, 2780},
        {2390, 2180, 1970, 2209, 839, 800, 0, 2930, 3380, 2400, 3300, 1600, 3400, 1500, 2290},
        {408, 852, 1004, 1367, 2330, 3460, 2930, 0, 711, 1550, 3800, 2800, 300, 1300, 507},
        {1109, 1553, 1710, 2027, 3010, 3910, 3380, 711, 0, 2210, 4400, 3400, 476, 1800, 1208},
        {925, 1340, 906, 209, 1640, 2390, 2400, 1550, 2210, 0, 2800, 1800, 1930, 1270, 1024},
        {3500, 3200, 3100, 2700, 4200, 3300, 3300, 3800, 4400, 2800, 0, 1300, 4300, 3800, 3490},
        {2600, 2400, 2200, 1800, 1600, 1600, 1600, 2800, 3400, 1800, 1300, 0, 3100, 2600, 2590},
        {705, 1135, 1410, 1730, 2980, 3720, 3400, 300, 476, 1930, 4300, 3100, 0, 1600, 804},
        {881, 521, 524, 1190, 1200, 1850, 1500, 1300, 1800, 1270, 3800, 2600, 1600, 0, 780},
        {99, 360, 583, 873, 1860, 2780, 2290, 507, 1208, 1024, 3490, 2590, 804, 780, 0}
    };

    // Constantes do sistema
    const double TEMPO_MAX_DIRECAO = 5.5;
    const double VELOCIDADE_MAXIMA = 120.0;
    
    // Variáveis do computador de bordo (persistentes)
    double quilometragem_total = 0.0;
    double total_gasto_combustivel = 0.0;
    double total_gasto_dinheiro = 0.0;
    
    // Variáveis de controle
    int opcao;
    double distancia, velocidade;
    int cidade_origem, cidade_destino;
    int combustivel_escolhido;
    double consumo_personalizado;
    double capacidade_tanque, combustivel_atual;
    char continuar;
    
    cout << "**********************************************\n";
    cout << "*        SISTEMA COMPUTADOR DE BORDO        *\n";
    cout << "*    Monitoramento e Planejamento de Viagem *\n";
    cout << "**********************************************\n\n";

    do {
        cout << "==============================================\n";
        cout << "          SELECIONE O TIPO DE VIAGEM         \n";
        cout << "==============================================\n";
        cout << "1. Viagem entre cidades\n";
        cout << "2. Viagem por distancia manual\n";
        cout << "3. Estatisticas do veiculo\n";
        cout << "4. Sair do sistema\n";
        cout << "----------------------------------------------\n";
        cout << "Digite sua opcao (1-4): ";
        cin >> opcao;
        
        if (opcao == 4) {
            cout << "\nObrigado por usar o sistema! Volte sempre.\n";
            break;
        }
        
        if (opcao == 3) {
            cout << "\n==============================================\n";
            cout << "          ESTATISTICAS DO VEICULO           \n";
            cout << "==============================================\n";
            cout << "Quilometragem total: " << quilometragem_total << " km\n";
            cout << "Total de combustivel gasto: " << total_gasto_combustivel << " L\n";
            cout << "Total gasto em viagens: R$ " << total_gasto_dinheiro << "\n";
            if (quilometragem_total > 0) {
                cout << "Consumo medio: " << (quilometragem_total / total_gasto_combustivel) << " km/L\n";
            }
            cout << "==============================================\n\n";
            continue;
        }
        
        if (opcao != 1 && opcao != 2) {
            cout << "\n>>> ERRO: Opcao invalida! Tente novamente.\n\n";
            continue;
        }
        
        // OBTER DISTANCIA
        cout << "\n==============================================\n";
        cout << "           INFORMACOES DA VIAGEM           \n";
        cout << "==============================================\n";
        
        if (opcao == 1) {
            cout << "\nLISTA DE CIDADES DISPONIVEIS:\n";
            cout << "------------------------------\n";
            for (int i = 0; i < NUM_CIDADES; i++) {
                cout << setw(2) << (i + 1) << ". " << cidades[i] << "\n";
            }
            
            while (true) {
                cout << "\nDigite o numero da cidade de ORIGEM: ";
                cin >> cidade_origem;
                cout << "Digite o numero da cidade de DESTINO: ";
                cin >> cidade_destino;
                
                if (cidade_origem >= 1 && cidade_origem <= NUM_CIDADES &&
                    cidade_destino >= 1 && cidade_destino <= NUM_CIDADES) {
                    
                    if (cidade_origem == cidade_destino) {
                        cout << ">>> ERRO: Origem e destino nao podem ser iguais!\n";
                        continue;
                    }
                    break;
                } else {
                    cout << ">>> ERRO: Numeros invalidos! Use valores entre 1 e " << NUM_CIDADES << ".\n";
                }
            }
            
            cidade_origem--;
            cidade_destino--;
            distancia = distancias[cidade_origem][cidade_destino];
            
            cout << "\n--- ROTA SELECIONADA ---\n";
            cout << "ORIGEM:  " << cidades[cidade_origem] << "\n";
            cout << "DESTINO: " << cidades[cidade_destino] << "\n";
            cout << "DISTANCIA: " << distancia << " km\n";
            
        } else {
            while (true) {
                cout << "\nDigite a distancia da viagem (km): ";
                cin >> distancia;
                if (distancia > 0 && distancia <= 10000) {
                    break;
                }
                cout << ">>> ERRO: Distancia invalida! Use valores entre 1 e 10000 km.\n";
            }
            cout << "DISTANCIA DEFINIDA: " << distancia << " km\n";
        }
        
        // ENTRADA DA VELOCIDADE
        cout << "\n==============================================\n";
        cout << "          VELOCIDADE DE VIAGEM            \n";
        cout << "==============================================\n";
        
        while (true) {
            cout << "Digite a velocidade media planejada (km/h): ";
            cin >> velocidade;
            if (velocidade > 0 && velocidade <= VELOCIDADE_MAXIMA) {
                break;
            }
            cout << ">>> ERRO: Velocidade invalida! Use valores entre 1 e " << VELOCIDADE_MAXIMA << " km/h.\n";
        }
        cout << "VELOCIDADE DEFINIDA: " << velocidade << " km/h\n";
        
        // SELEÇÃO DE COMBUSTÍVEL
        cout << "\n==============================================\n";
        cout << "          TIPO DE COMBUSTIVEL              \n";
        cout << "==============================================\n";
        cout << "COMBUSTIVEIS DISPONIVEIS:\n";
        cout << "----------------------------------------------\n";
        for (int i = 0; i < NUM_COMBUSTIVEIS; i++) {
            cout << (i + 1) << ". " << nomes_combustiveis[i] << "\n";
            cout << "   Preco: R$ " << precos_combustiveis[i] << "/" << unidades_combustiveis[i] << "\n";
            cout << "   Consumo ideal: " << consumos_combustiveis[i] << " km/" << unidades_combustiveis[i] << "\n";
            cout << "----------------------------------------------\n";
        }
        
        while (true) {
            cout << "Escolha o tipo de combustivel (1-" << NUM_COMBUSTIVEIS << "): ";
            cin >> combustivel_escolhido;
            if (combustivel_escolhido >= 1 && combustivel_escolhido <= NUM_COMBUSTIVEIS) {
                combustivel_escolhido--;
                break;
            }
            cout << ">>> ERRO: Combustivel invalido! Escolha entre 1 e " << NUM_COMBUSTIVEIS << ".\n";
        }
        
        cout << "COMBUSTIVEL SELECIONADO: " << nomes_combustiveis[combustivel_escolhido] << "\n";
        
        // CONSUMO PERSONALIZADO
        cout << "\n==============================================\n";
        cout << "         CONSUMO DO VEICULO               \n";
        cout << "==============================================\n";
        
        char opcao_consumo;
        double consumo_base = consumos_combustiveis[combustivel_escolhido];
        double consumo_real;
        
        cout << "Consumo ideal do " << nomes_combustiveis[combustivel_escolhido] << ": ";
        cout << consumo_base << " km/" << unidades_combustiveis[combustivel_escolhido] << "\n";
        
        cout << "Deseja usar consumo personalizado? (S/N): ";
        cin >> opcao_consumo;
        
        if (opcao_consumo == 'S' || opcao_consumo == 's') {
            while (true) {
                cout << "Digite o consumo real do seu veiculo (km/" << unidades_combustiveis[combustivel_escolhido] << "): ";
                cin >> consumo_personalizado;
                if (consumo_personalizado > 0 && consumo_personalizado <= 50) {
                    consumo_real = consumo_personalizado;
                    break;
                }
                cout << ">>> ERRO: Consumo invalido! Use valores entre 1 e 50.\n";
            }
            cout << "CONSUMO PERSONALIZADO DEFINIDO: " << consumo_real << " km/" << unidades_combustiveis[combustivel_escolhido] << "\n";
        } else {
            // CALCULAR PERDAS DE DESEMPENHO REALISTAS
            cout << "\n--- CALCULANDO PERDAS DE DESEMPENHO ---\n";
            
            consumo_real = consumo_base;
            
            // 1. Perda por velocidade (regra: +5km/h -0,5km/L a partir de 80km/h)
            double perda_velocidade = 0.0;
            if (velocidade > 80) {
                double excesso = velocidade - 80;
                double incrementos = excesso / 5.0;
                perda_velocidade = incrementos * 0.5; // -0,5km/L por cada 5km/h acima de 80
                
                if (perda_velocidade > (consumo_real * 0.4)) {
                    perda_velocidade = consumo_real * 0.4; // Limite máximo de 40% de perda
                }
                
                consumo_real -= perda_velocidade;
                cout << "Perda por velocidade (" << velocidade << " km/h): -" << perda_velocidade << " km/L\n";
            }
            
            // 2. Perda por condições da estrada
            double perda_estrada = consumo_real * 0.08;
            consumo_real -= perda_estrada;
            cout << "Perda por condicoes da estrada: -" << perda_estrada << " km/L\n";
            
            // 3. Perda por carga e uso do ar condicionado
            double perda_carga = consumo_real * 0.05;
            consumo_real -= perda_carga;
            cout << "Perda por carga e ar condicionado: -" << perda_carga << " km/L\n";
            
            cout << "CONSUMO REAL ESTIMADO: " << consumo_real << " km/" << unidades_combustiveis[combustivel_escolhido] << "\n";
        }
        
        // DADOS DO VEÍCULO
        cout << "\n==============================================\n";
        cout << "           DADOS DO VEICULO                \n";
        cout << "==============================================\n";
        
        while (true) {
            cout << "Capacidade total do tanque (" << unidades_combustiveis[combustivel_escolhido] << "): ";
            cin >> capacidade_tanque;
            if (capacidade_tanque > 0 && capacidade_tanque <= 500) {
                break;
            }
            cout << ">>> ERRO: Capacidade invalida! Use valores entre 1 e 500.\n";
        }
        
        while (true) {
            cout << "Combustivel atual no tanque (" << unidades_combustiveis[combustivel_escolhido] << "): ";
            cin >> combustivel_atual;
            if (combustivel_atual >= 0 && combustivel_atual <= capacidade_tanque) {
                break;
            }
            cout << ">>> ERRO: Quantidade invalida! Use valores entre 0 e " << capacidade_tanque << ".\n";
        }
        
        // CÁLCULOS E RESULTADOS
        cout << "\n";
        cout << "==============================================\n";
        cout << "          CALCULANDO RESULTADOS...         \n";
        cout << "==============================================\n";
        
        // Cálculos básicos
        double tempo_viagem = distancia / velocidade;
        int horas = tempo_viagem;
        int minutos = (tempo_viagem - horas) * 60;
        
        double combustivel_necessario = distancia / consumo_real;
        double combustivel_faltante = combustivel_necessario - combustivel_atual;
        if (combustivel_faltante < 0) combustivel_faltante = 0;
        
        double custo_total = combustivel_necessario * precos_combustiveis[combustivel_escolhido];
        
        // Cálculos de autonomia
        double autonomia_atual = combustivel_atual * consumo_real;
        double tempo_ate_acabar = autonomia_atual / velocidade;
        int horas_ate_acabar = tempo_ate_acabar;
        int minutos_ate_acabar = (tempo_ate_acabar - horas_ate_acabar) * 60;
        
        // EXIBIÇÃO DOS RESULTADOS
        cout << "**********************************************\n";
        cout << "*        COMPUTADOR DE BORDO - RELATORIO    *\n";
        cout << "**********************************************\n\n";
        
        // Seção 1: Informações da Viagem
        cout << "1. INFORMACOES DA VIAGEM:\n";
        cout << "--------------------------\n";
        if (opcao == 1) {
            cout << "   Rota: " << cidades[cidade_origem] << " para " << cidades[cidade_destino] << "\n";
        }
        cout << "   Distancia total: " << distancia << " km\n";
        cout << "   Velocidade media: " << velocidade << " km/h\n";
        cout << "   Tempo de viagem: " << horas << " horas e " << minutos << " minutos\n";
        cout << "\n";
        
        // Seção 2: Informações do Combustível
        cout << "2. DADOS DE COMBUSTIVEL:\n";
        cout << "-------------------------\n";
        cout << "   Tipo: " << nomes_combustiveis[combustivel_escolhido] << "\n";
        cout << "   Preco: R$ " << precos_combustiveis[combustivel_escolhido] << "/" << unidades_combustiveis[combustivel_escolhido] << "\n";
        cout << "   Consumo REAL: " << consumo_real << " km/" << unidades_combustiveis[combustivel_escolhido] << "\n";
        cout << "   Combustivel necessario: " << combustivel_necessario << " " << unidades_combustiveis[combustivel_escolhido] << "\n";
        cout << "   Combustivel disponivel: " << combustivel_atual << " " << unidades_combustiveis[combustivel_escolhido] << "\n";
        cout << "   Autonomia atual: " << autonomia_atual << " km\n";
        cout << "\n";
        
        // Seção 3: Análise de Viabilidade
        cout << "3. ANALISE DE VIABILIDADE:\n";
        cout << "--------------------------\n";
        
        bool alertas = false;
        
        if (autonomia_atual < distancia) {
            cout << "   [ALERTA] COMBUSTIVEL INSUFICIENTE\n";
            cout << "   - Autonomia atual: " << autonomia_atual << " km\n";
            cout << "   - Distancia necessaria: " << distancia << " km\n";
            cout << "   - Faltam: " << (distancia - autonomia_atual) << " km\n";
            cout << "   - Combustivel acabara em: " << horas_ate_acabar << "h " << minutos_ate_acabar << "min\n";
            alertas = true;
            
            if (combustivel_faltante > 0) {
                cout << "\n   PLANO DE ABASTECIMENTO:\n";
                double combustivel_restante = combustivel_faltante;
                int parada_num = 1;
                double custo_total_abastecimento = 0;
                
                while (combustivel_restante > 0 && parada_num <= 5) {
                    double abastecer = combustivel_restante;
                    if (abastecer > capacidade_tanque) {
                        abastecer = capacidade_tanque;
                    }
                    
                    double custo_parada = abastecer * precos_combustiveis[combustivel_escolhido];
                    custo_total_abastecimento += custo_parada;
                    
                    cout << "   Parada " << parada_num << ": " << abastecer << " " << unidades_combustiveis[combustivel_escolhido];
                    cout << " (R$ " << custo_parada << ")\n";
                    
                    combustivel_restante -= abastecer;
                    parada_num++;
                }
                cout << "   Custo total do abastecimento: R$ " << custo_total_abastecimento << "\n";
            }
        } else {
            cout << "   [OK] Combustivel suficiente para a viagem\n";
        }
        
        if (velocidade > 100) {
            cout << "   [ATENCAO] VELOCIDADE ELEVADA - Aumenta consumo em " << ((velocidade - 80) / 5 * 0.5) << " km/L\n";
            alertas = true;
        }
        
        if (tempo_viagem >= TEMPO_MAX_DIRECAO) {
            cout << "   [ALERTA] TEMPO DE VIAGEM LONGO\n";
            int paradas_descanso = tempo_viagem / TEMPO_MAX_DIRECAO;
            cout << "   - Paradas para descanso recomendadas: " << paradas_descanso << "\n";
            alertas = true;
        }
        
        if (!alertas) {
            cout << "   [OK] Todas as verificacoes de seguranca atendidas\n";
        }
        cout << "\n";
        
        // Seção 4: Custos
        cout << "4. ORCAMENTO DA VIAGEM:\n";
        cout << "-----------------------\n";
        cout << "   Custo com combustivel: R$ " << custo_total << "\n";
        
        if (combustivel_faltante > 0) {
            double custo_abastecimento = combustivel_faltante * precos_combustiveis[combustivel_escolhido];
            cout << "   Custo adicional de abastecimento: R$ " << custo_abastecimento << "\n";
            double custo_total_com_abastecimento = custo_total + custo_abastecimento;
            cout << "   Custo total da viagem: R$ " << custo_total_com_abastecimento << "\n";
        } else {
            cout << "   Custo total da viagem: R$ " << custo_total << "\n";
        }
        cout << "\n";
        
        // Seção 5: Resumo Executivo
        cout << "5. RESUMO EXECUTIVO:\n";
        cout << "--------------------\n";
        cout << "   Distancia: " << distancia << " km\n";
        cout << "   Tempo: " << horas << "h " << minutos << "min\n";
        cout << "   Combustivel: " << nomes_combustiveis[combustivel_escolhido] << "\n";
        cout << "   Autonomia: " << autonomia_atual << " km\n";
        cout << "   Custo total: R$ " << custo_total << "\n";
        
        if (autonomia_atual >= distancia) {
            cout << "   STATUS: VIAGEM VIAVEL\n";
        } else {
            cout << "   STATUS: NECESSARIO ABASTECIMENTO\n";
        }
        
        // Atualizar estatísticas do computador de bordo
        quilometragem_total += distancia;
        total_gasto_combustivel += combustivel_necessario;
        total_gasto_dinheiro += custo_total;
        
        cout << "\n**********************************************\n";
        cout << "*         FIM DO RELATORIO                *\n";
        cout << "**********************************************\n\n";
        
        // Opção de continuar
        cout << "Deseja realizar outro calculo? (S/N): ";
        cin >> continuar;
        cout << "\n";
        
    } while (continuar == 'S' || continuar == 's');
    
    // Estatísticas finais
    cout << "==============================================\n";
    cout << "         ESTATISTICAS FINAIS DO VEICULO     \n";
    cout << "==============================================\n";
    cout << "Quilometragem total percorrida: " << quilometragem_total << " km\n";
    cout << "Total de combustivel gasto: " << total_gasto_combustivel << " L\n";
    cout << "Total investido em viagens: R$ " << total_gasto_dinheiro << "\n";
    if (quilometragem_total > 0) {
        cout << "Consumo medio do veiculo: " << (quilometragem_total / total_gasto_combustivel) << " km/L\n";
    }
    cout << "==============================================\n";
    cout << "    Obrigado por usar o Computador de Bordo!\n";
    cout << "         Dirija com seguranca!               \n";
    cout << "==============================================\n";
    
    return 0;
}